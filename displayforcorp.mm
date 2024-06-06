#import <Cocoa/Cocoa.h>

@interface DrawingView : NSView
@property (nonatomic) NSRect rectangleRect;
@property (nonatomic) BOOL isDrawing;
@end

@implementation DrawingView

- (instancetype)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    if (self) {
        _isDrawing = NO;
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    if (self.isDrawing) {
        NSColor *color = [NSColor colorWithCalibratedRed:0.0 green:0.0 blue:1.0 alpha:0.5];
        [color setFill];
        NSBezierPath *path = [NSBezierPath bezierPathWithRect:self.rectangleRect];
        [path fill];
    }
}

- (void)mouseDown:(NSEvent *)event {
    NSPoint startPoint = [self convertPoint:[event locationInWindow] fromView:nil];
    self.rectangleRect = NSMakeRect(startPoint.x, startPoint.y, 0, 0);
    self.isDrawing = YES;
    [self setNeedsDisplay:YES];
}

- (void)mouseDragged:(NSEvent *)event {
    NSPoint currentPoint = [self convertPoint:[event locationInWindow] fromView:nil];
    CGFloat width = currentPoint.x - self.rectangleRect.origin.x;
    CGFloat height = currentPoint.y - self.rectangleRect.origin.y;
    self.rectangleRect.size = NSMakeSize(width, height);
    [self setNeedsDisplay:YES];
}

- (void)mouseUp:(NSEvent *)event {
    self.isDrawing = NO;
    [self setNeedsDisplay:YES];
    
    // Print the dimensions of the rectangle
    NSLog(@"Top: %f, Bottom: %f, Left: %f, Right: %f",
          self.rectangleRect.origin.y + self.rectangleRect.size.height,
          self.rectangleRect.origin.y,
          self.rectangleRect.origin.x,
          self.rectangleRect.origin.x + self.rectangleRect.size.width);
}

@end

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation AppDelegate {
    NSWindow *_window;
    DrawingView *_drawingView;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    NSRect frame = NSMakeRect(0, 0, 400, 400);
    _window = [[NSWindow alloc] initWithContentRect:frame
                                           styleMask:(NSWindowStyleMaskTitled |
                                                      NSWindowStyleMaskClosable |
                                                      NSWindowStyleMaskResizable)
                                             backing:NSBackingStoreBuffered
                                               defer:NO];
    [_window setTitle:@"Image Display"];
    [_window makeKeyAndOrderFront:nil];

    const int width = 3;
    const int height = 3;
    unsigned char image[width * height * 3] = {
        255, 0, 0,   // Red
        0, 255, 0,   // Green
        0, 0, 255,   // Blue
        255, 255, 0,   // Yellow
        0, 255, 255,   // Cyan
        255, 0, 255,   // Magenta
        192, 192, 192, // Silver
        128, 128, 128, // Gray
        0, 0, 0      // Black
    };

    NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:NULL
                                                                       pixelsWide:width
                                                                       pixelsHigh:height
                                                                    bitsPerSample:8
                                                                  samplesPerPixel:3
                                                                         hasAlpha:NO
                                                                         isPlanar:NO
                                                                   colorSpaceName:NSCalibratedRGBColorSpace
                                                                     bitmapFormat:0
                                                                      bytesPerRow:width * 3
                                                                     bitsPerPixel:24];

    memcpy([bitmap bitmapData], image, width * height * 3);

    NSImage *nsImage = [[NSImage alloc] initWithSize:NSMakeSize(width, height)];
    [nsImage addRepresentation:bitmap];

    NSImageView *imageView = [[NSImageView alloc] initWithFrame:frame];
    [imageView setImage:nsImage];
    [imageView setImageScaling:NSImageScaleAxesIndependently];

    [[_window contentView] addSubview:imageView];

    _drawingView = [[DrawingView alloc] initWithFrame:frame];
    [[_window contentView] addSubview:_drawingView];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];
        [app run];
    }
    return 0;
}
