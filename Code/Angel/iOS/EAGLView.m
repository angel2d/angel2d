//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2012, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#import "EAGLView.h"

#import "ES1Renderer.h"

#include "iPhoneMain.h"
#include "../Angel.h"

@implementation EAGLView

@synthesize animating;
@dynamic animationFrameInterval;

// You must implement this method
+ (Class)layerClass
{
	return [CAEAGLLayer class];
}

//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder
{
	if ((self = [super initWithCoder:coder]))
	{
		// Get the layer
		CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;

		eaglLayer.opaque = TRUE;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

		renderer = [[ES1Renderer alloc] init];
		
		if (!renderer)
		{
			[self release];
			return nil;
		}

		animating = FALSE;
		displayLinkSupported = FALSE;
		animationFrameInterval = 1;
		displayLink = nil;
		animationTimer = nil;

		// A system version of 3.1 or greater is required to use CADisplayLink. The NSTimer
		// class is used as fallback when it isn't available.
		NSString *reqSysVer = @"3.1";
		NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
		if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
			displayLinkSupported = TRUE;
		
		UIScreen* mainscr = [UIScreen mainScreen];
		int screenW = mainscr.currentMode.size.width;
		int screenH = mainscr.currentMode.size.height;
		
		CGRect bounds = [eaglLayer bounds];
		int layerW = bounds.size.width;
		int layerH = bounds.size.height;
		
		int w, h;
		bool highRes = false;
		if (screenW == 2 * layerW)
		{
			w = screenW;
			h = screenH;
			self.contentScaleFactor = 2.0;
			highRes = true;
		}
		else 
		{
			w = layerW;
			h = layerH;
		}
		
		theWorld.SetHighResolutionScreen(highRes);
		theWorld.Initialize(h, w);
		
		[self setupGestureRecognizers];
		
		AngelGameInit();
		theSwitchboard.Broadcast(new Message("GameStart"));
	}

	return self;
}

Vec2i __invertXY(int x, int y)
{
	int camHeight = theCamera.GetWindowHeight();
	if (theWorld.IsHighResScreen())
	{
		camHeight /= 2;
	}
	return Vec2i(y, camHeight - x);
}

- (void)setupGestureRecognizers
{
	UISwipeGestureRecognizer *swipeRecognizer;
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionLeft;
	swipeRecognizer.cancelsTouchesInView = NO;
	[self addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionRight;
	swipeRecognizer.cancelsTouchesInView = NO;
	[self addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionUp;
	swipeRecognizer.cancelsTouchesInView = NO;
	[self addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionDown;
	swipeRecognizer.cancelsTouchesInView = NO;
	[self addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	
	UIPinchGestureRecognizer *pinchRecognizer;
	pinchRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinchGesture:)];
	pinchRecognizer.cancelsTouchesInView = NO;
	[self addGestureRecognizer:pinchRecognizer];
	[pinchRecognizer release];
	
	UIRotationGestureRecognizer *rotationRecognizer;
	rotationRecognizer = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(handleRotationGesture:)];
	rotationRecognizer.cancelsTouchesInView = NO;
	[self addGestureRecognizer:rotationRecognizer];
	[rotationRecognizer release];
}

- (void)handleSwipeGesture:(UISwipeGestureRecognizer*)recognizer
{
	// the touches are rotated because we're in landscape mode
	if (recognizer.direction == UISwipeGestureRecognizerDirectionLeft)
	{
		// Down
		theSwitchboard.Broadcast(new Message("MultiTouchSwipeDown"));
	}
	else if (recognizer.direction == UISwipeGestureRecognizerDirectionRight)
	{
		// Up
		theSwitchboard.Broadcast(new Message("MultiTouchSwipeUp"));
	}
	else if (recognizer.direction == UISwipeGestureRecognizerDirectionUp)
	{
		// Left
		theSwitchboard.Broadcast(new Message("MultiTouchSwipeLeft"));
	}
	else if (recognizer.direction == UISwipeGestureRecognizerDirectionDown)
	{
		// Right
		theSwitchboard.Broadcast(new Message("MultiTouchSwipeRight"));
	}
}

- (void)handlePinchGesture:(UIPinchGestureRecognizer*)recognizer
{
	GestureData gd;
	gd.Velocity = recognizer.velocity;
	gd.GestureMagnitude = recognizer.scale;
	theSwitchboard.Broadcast(new TypedMessage<GestureData>("MultiTouchPinch", gd));
}

- (void)handleRotationGesture:(UIRotationGestureRecognizer*)recognizer
{
	GestureData gd;
	gd.Velocity = recognizer.velocity;
	gd.GestureMagnitude = -recognizer.rotation;
	theSwitchboard.Broadcast(new TypedMessage<GestureData>("MultiTouchRotate", gd));
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	// find the new touches and add them to the list
	NSEnumerator *it = [touches objectEnumerator];
	id touchID;
	
	TouchList* tl = &TouchListener::GetTouchList();
	
	while (touchID = [it nextObject])
	{
		UITouch* touch = (UITouch*)touchID;
		if (UITouchPhaseBegan == touch.phase)
		{
			CGPoint loc = [touch locationInView:self];
			Touch* t = new Touch();
			t->__platformTouch = touch;
			t->StartingPoint = __invertXY(loc.x, loc.y);
			t->CurrentPoint = t->StartingPoint;
			tl->push_back(t);
			SendTouchNotifiers(t, TOUCH_START);
		}
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	NSEnumerator *touchEnum = [touches objectEnumerator];
	id touchID;
	
	TouchList* tl = &TouchListener::GetTouchList();
	
	while (touchID = [touchEnum nextObject])
	{
		UITouch* touch = (UITouch*)touchID;
		if (UITouchPhaseMoved == touch.phase)
		{
			for (unsigned int i=0; i < tl->size(); i++)
			{
				if ((*tl)[i]->__platformTouch == touch)
				{
					CGPoint loc = [touch locationInView:self];
					(*tl)[i]->CurrentPoint = __invertXY(loc.x, loc.y);
					if ( (*tl)[i]->MotionStartTime < 0.0f )
					{
						(*tl)[i]->MotionStartTime = theWorld.GetCurrentTimeSeconds();
					}
					SendTouchNotifiers((*tl)[i], TOUCH_MOVE);
				}
			}
		}
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self touchesEnded:touches withEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	// find the ended touches and remove them from the list
	NSEnumerator *touchEnum = [touches objectEnumerator];
	id touchID;
	
	TouchList* tl = &TouchListener::GetTouchList();
	
	while (touchID = [touchEnum nextObject])
	{
		UITouch* touch = (UITouch*)touchID;
		if (UITouchPhaseEnded == touch.phase)
		{
			TouchList::iterator it = tl->begin();
			while (it != tl->end())
			{
				if ((*it)->__platformTouch == touch)
				{
					break;
				}
				it++;
			}
			if (it != tl->end())
			{
				SendTouchNotifiers((*it), TOUCH_END);
				delete (*it);
				tl->erase(it);
			}
		}
	}
}

- (void)drawView:(id)sender
{
	[renderer render];
}

- (void)layoutSubviews
{
	[renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
	[self drawView:nil];
}

- (NSInteger)animationFrameInterval
{
	return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame interval is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;

		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void)startAnimation
{
	if (!animating)
	{
		if (displayLinkSupported)
		{
			// CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result in a warning, but can be dismissed
			// if the system version runtime check for CADisplayLink exists in -initWithCoder:. The runtime check ensures this code will
			// not be called in system versions earlier than 3.1.

			displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
			[displayLink setFrameInterval:animationFrameInterval];
			[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		}
		else
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * animationFrameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];

		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
		if (displayLinkSupported)
		{
			[displayLink invalidate];
			displayLink = nil;
		}
		else
		{
			[animationTimer invalidate];
			animationTimer = nil;
		}

		animating = FALSE;
	}
}

- (void)dealloc
{
	[renderer release];

	[super dealloc];
}

@end
