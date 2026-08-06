#import <Cocoa/Cocoa.h>

#include "macos_window.h"

namespace
{
bool keyIsDown(CGKeyCode keyCode)
{
    return CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,
                                 keyCode);
}
}

std::size_t getDisplayCount()
{
    return [[NSScreen screens] count];
}

sf::Vector2u getDisplaySize(std::size_t displayIndex)
{
    NSArray<NSScreen*>* screens = [NSScreen screens];
    if (displayIndex >= [screens count]) {
        return {800u, 800u};
    }

    const NSSize displaySize = [screens[displayIndex] frame].size;
    return {static_cast<unsigned int>(displaySize.width),
            static_cast<unsigned int>(displaySize.height)};
}

sf::Vector2u configureWindowForDisplay(sf::WindowHandle handle,
                                       std::size_t displayIndex)
{
    id nativeObject = (__bridge id)handle;
    NSWindow* window = [nativeObject isKindOfClass:[NSWindow class]]
                           ? (NSWindow*)nativeObject
                           : [nativeObject window];

    [window setStyleMask:NSWindowStyleMaskBorderless];
    [window setIgnoresMouseEvents:YES];
    [window setMovable:NO];
    [window setLevel:CGWindowLevelForKey(kCGDesktopIconWindowLevelKey) - 1];
    [window setCollectionBehavior:NSWindowCollectionBehaviorCanJoinAllSpaces |
                                  NSWindowCollectionBehaviorStationary |
                                  NSWindowCollectionBehaviorIgnoresCycle];
    [window setHidesOnDeactivate:NO];

    NSArray<NSScreen*>* screens = [NSScreen screens];
    if (displayIndex < [screens count]) {
        const NSRect displayFrame = [screens[displayIndex] frame];
        [window setFrame:displayFrame display:YES];
        [window orderFrontRegardless];
        return {static_cast<unsigned int>(displayFrame.size.width),
                static_cast<unsigned int>(displayFrame.size.height)};
    }

    const NSSize windowSize = [window frame].size;
    return {static_cast<unsigned int>(windowSize.width),
            static_cast<unsigned int>(windowSize.height)};
}

sf::Vector2f getNormalizedMousePosition(sf::WindowHandle handle)
{
    id nativeObject = (__bridge id)handle;
    NSWindow* window = [nativeObject isKindOfClass:[NSWindow class]]
                           ? (NSWindow*)nativeObject
                           : [nativeObject window];
    NSView* contentView = [window contentView];
    const NSRect bounds = [contentView bounds];
    const NSPoint windowPoint = [window mouseLocationOutsideOfEventStream];
    const NSPoint contentPoint = [contentView convertPoint:windowPoint fromView:nil];

    if (!NSPointInRect(contentPoint, bounds) || bounds.size.width <= 0.0 ||
        bounds.size.height <= 0.0) {
        return {-1.f, -1.f};
    }

    const float normalizedX = static_cast<float>(
        (contentPoint.x - NSMinX(bounds)) / bounds.size.width);
    const float normalizedY = static_cast<float>(
        (NSMaxY(bounds) - contentPoint.y) / bounds.size.height);
    return {normalizedX, normalizedY};
}

bool consumePainterToggleShortcut()
{
    constexpr CGKeyCode escapeKey = 53;
    static bool wasDown = false;

    const bool isDown = keyIsDown(escapeKey);
    const bool wasPressed = isDown && !wasDown;
    wasDown = isDown;
    return wasPressed;
}

void setWindowPainterMode(sf::WindowHandle handle, bool enabled)
{
    id nativeObject = (__bridge id)handle;
    NSWindow* window = [nativeObject isKindOfClass:[NSWindow class]]
                           ? (NSWindow*)nativeObject
                           : [nativeObject window];

    [window setIgnoresMouseEvents:!enabled];
    [window setLevel:enabled ? NSNormalWindowLevel
                             : CGWindowLevelForKey(kCGDesktopIconWindowLevelKey) - 1];
    if (enabled) {
        [window orderFrontRegardless];
    }
}
