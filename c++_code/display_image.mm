#import <Cocoa/Cocoa.h>
#include <iostream>
#include <cstring>

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@end

@implementation AppDelegate {
    NSWindow *_window;
    NSImageView *_imageView;
    int *_flattenedImageData;
    int _height;
    int _width;
    int _channels;
}

- (instancetype)initWithImageData:(int *)imageData height:(int)height width:(int)width channels:(int)channels {
    self = [super init];
    if (self) {
        _flattenedImageData = imageData;
        _height = height;
        _width = width;
        _channels = channels;
    }
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    // Process the image data in a background thread
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        // Get screen size
        NSRect screenFrame = [[NSScreen mainScreen] visibleFrame];
        CGFloat screenWidth = screenFrame.size.width;
        CGFloat screenHeight = screenFrame.size.height;

        // Set the maximum window size
        CGFloat maxWindowSize = 500;

        // Set the initial window size and ensure it fits the screen
        CGFloat windowWidth = self->_width;
        CGFloat windowHeight = self->_height;
        CGFloat aspectRatio = (CGFloat)self->_width / (CGFloat)self->_height;

        if (windowWidth > maxWindowSize || windowHeight > maxWindowSize) {
            if (windowWidth > windowHeight) {
                windowWidth = maxWindowSize;
                windowHeight = windowWidth / aspectRatio;
            } else {
                windowHeight = maxWindowSize;
                windowWidth = windowHeight * aspectRatio;
            }
        } else if (windowWidth < maxWindowSize || windowHeight < maxWindowSize) {
            if (windowWidth < windowHeight) {
                windowWidth = maxWindowSize;
                windowHeight = windowWidth / aspectRatio;
            } else {
                windowHeight = maxWindowSize;
                windowWidth = windowHeight * aspectRatio;
            }
        }

        if (windowWidth > screenWidth) {
            windowWidth = screenWidth;
            windowHeight = windowWidth / aspectRatio;
        }
        if (windowHeight > screenHeight) {
            windowHeight = screenHeight;
            windowWidth = windowHeight * aspectRatio;
        }

        NSRect frame = NSMakeRect(0, 0, windowWidth, windowHeight);

        // Create a bitmap image rep from the raw data
        NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:NULL
                                                                           pixelsWide:self->_width
                                                                           pixelsHigh:self->_height
                                                                        bitsPerSample:8
                                                                      samplesPerPixel:self->_channels
                                                                             hasAlpha:NO
                                                                             isPlanar:NO
                                                                       colorSpaceName:NSCalibratedRGBColorSpace
                                                                         bitmapFormat:0
                                                                          bytesPerRow:self->_width * self->_channels
                                                                         bitsPerPixel:8 * self->_channels];

        // Copy image data to bitmap and convert BGR to RGB
        unsigned char *dataPtr = [bitmap bitmapData];
        for (int i = 0; i < self->_height; ++i) {
            for (int j = 0; j < self->_width; ++j) {
                for (int k = 0; k < self->_channels; ++k) {
                    int value = self->_flattenedImageData[i * self->_width * self->_channels + j * self->_channels + k];
                    if (value < 0) value = 0;
                    if (value > 255) value = 255;

                    // Swap B and R channels
                    if (k == 0) {
                        *dataPtr++ = (unsigned char)self->_flattenedImageData[i * self->_width * self->_channels + j * self->_channels + 2];  // B
                    } else if (k == 2) {
                        *dataPtr++ = (unsigned char)self->_flattenedImageData[i * self->_width * self->_channels + j * self->_channels + 0];  // R
                    } else {
                        *dataPtr++ = (unsigned char)value;  // G
                    }
                }
            }
        }

        // Create an NSImage and add the bitmap rep to it
        NSImage *nsImage = [[NSImage alloc] initWithSize:NSMakeSize(self->_width, self->_height)];
        [nsImage addRepresentation:bitmap];

        // Update the UI on the main thread
        dispatch_async(dispatch_get_main_queue(), ^{
            // Create the window
            self->_window = [[NSWindow alloc] initWithContentRect:frame
                                                        styleMask:(NSWindowStyleMaskTitled |
                                                                   NSWindowStyleMaskClosable |
                                                                   NSWindowStyleMaskResizable)
                                                          backing:NSBackingStoreBuffered
                                                            defer:NO];
            [self->_window setTitle:@"Image Display"];
            [self->_window makeKeyAndOrderFront:nil];
            [self->_window setDelegate:self];

            // Create an NSImageView to display the image
            self->_imageView = [[NSImageView alloc] initWithFrame:NSMakeRect(0, 0, windowWidth, windowHeight)];
            [self->_imageView setImage:nsImage];
            [self->_imageView setImageScaling:NSImageScaleAxesIndependently]; // Allow independent scaling

            // Add the image view to the window's content view
            [[self->_window contentView] addSubview:self->_imageView];
        });
    });
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

- (void)windowDidResize:(NSNotification *)notification {
    NSWindow *window = [notification object];
    NSRect bounds = [window contentRectForFrameRect:[window frame]];
    CGFloat newWidth = NSWidth(bounds);
    CGFloat newHeight = NSHeight(bounds);
    CGFloat newAspectRatio = newWidth / newHeight;
    if (newAspectRatio > (CGFloat)_width / (CGFloat)_height) {
        [_imageView setImageScaling:NSImageScaleAxesIndependently];
    } else {
        [_imageView setImageScaling:NSImageScaleProportionallyUpOrDown];
    }
    [_imageView setFrame:NSMakeRect(0, 0, newWidth, newHeight)];
}

@end

extern "C" {
    void display_image(int *data, int height, int width, int channels) {
        @autoreleasepool {
            NSApplication *app = [NSApplication sharedApplication];
            AppDelegate *delegate = [[AppDelegate alloc] initWithImageData:data height:height width:width channels:channels];
            [app setDelegate:delegate];
            [app run];
        }
    }
}
