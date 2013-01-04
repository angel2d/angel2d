//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

#import "AngelViewController.h"

#include "../../Angel/Angel.h"
#include "iPhoneMain.h"


@interface AngelViewController () {}

@property (strong, nonatomic) EAGLContext *context;

@end


@implementation AngelViewController

@synthesize context = _context;

- (void)dealloc
{
    [_context release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1] autorelease];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    [self setupGL];
}

- (void)viewDidUnload
{    
    [super viewDidUnload];
    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc. that aren't in use.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
	
	CGSize viewportSize = [UIScreen mainScreen].bounds.size;
		
	if (UIInterfaceOrientationIsLandscape([self interfaceOrientation]))
	{
		viewportSize = CGSizeMake(viewportSize.height, viewportSize.width);
	}
		
	bool highRes = false;
	if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)] && [[UIScreen mainScreen] scale] == 2){
		viewportSize = CGSizeMake(viewportSize.width * 2, viewportSize.height * 2);
		highRes = true;
	}

	theWorld.SetHighResolutionScreen(highRes);
	theWorld.Initialize(viewportSize.width, viewportSize.height);
	
	[self setupGestureRecognizers];
	
	AngelGameInit();
	theSwitchboard.Broadcast(new Message("GameStart"));
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
	theWorld.Destroy();
}

- (void)update
{
	theWorld.SetDT(self.timeSinceLastUpdate);
    theWorld.Tick();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	theWorld.Render();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

- (void)setupGestureRecognizers
{
	UISwipeGestureRecognizer *swipeRecognizer;
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionLeft;
	swipeRecognizer.numberOfTouchesRequired = 1;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionLeft;
	swipeRecognizer.numberOfTouchesRequired = 2;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionRight;
	swipeRecognizer.numberOfTouchesRequired = 1;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionRight;
	swipeRecognizer.numberOfTouchesRequired = 2;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionUp;
	swipeRecognizer.numberOfTouchesRequired = 1;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionUp;
	swipeRecognizer.numberOfTouchesRequired = 2;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionDown;
	swipeRecognizer.numberOfTouchesRequired = 1;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeGesture:)];
	swipeRecognizer.direction = UISwipeGestureRecognizerDirectionDown;
	swipeRecognizer.numberOfTouchesRequired = 2;
	swipeRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:swipeRecognizer];
	[swipeRecognizer release];
	
	
	
	UIPinchGestureRecognizer *pinchRecognizer;
	pinchRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinchGesture:)];
	pinchRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:pinchRecognizer];
	[pinchRecognizer release];
	
	UIRotationGestureRecognizer *rotationRecognizer;
	rotationRecognizer = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(handleRotationGesture:)];
	rotationRecognizer.cancelsTouchesInView = NO;
	[[self view] addGestureRecognizer:rotationRecognizer];
	[rotationRecognizer release];
}

- (void)handleSwipeGesture:(UISwipeGestureRecognizer*)recognizer
{
	if (recognizer.direction == UISwipeGestureRecognizerDirectionLeft)
	{
		if (recognizer.numberOfTouchesRequired == 1)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeLeft"));
		}
		else if (recognizer.numberOfTouchesRequired == 2)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeLeftDouble"));
		}
	}
	else if (recognizer.direction == UISwipeGestureRecognizerDirectionRight)
	{
		if (recognizer.numberOfTouchesRequired == 1)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeRight"));
		}
		else if (recognizer.numberOfTouchesRequired == 2)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeRightDouble"));
		}	
	}
	else if (recognizer.direction == UISwipeGestureRecognizerDirectionUp)
	{
		if (recognizer.numberOfTouchesRequired == 1)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeUp"));
		}
		else if (recognizer.numberOfTouchesRequired == 2)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeUpDouble"));
		}
	}
	else if (recognizer.direction == UISwipeGestureRecognizerDirectionDown)
	{
		if (recognizer.numberOfTouchesRequired == 1)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeDown"));
		}
		else if (recognizer.numberOfTouchesRequired == 2)
		{
			theSwitchboard.Broadcast(new Message("MultiTouchSwipeDownDouble"));
		}
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
			CGPoint loc = [touch locationInView:[self view]];
			Touch* t = new Touch();
			t->__platformTouch = touch;
			t->StartingPoint = Vec2i(loc.x, loc.y);
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
					CGPoint loc = [touch locationInView:[self view]];
					(*tl)[i]->CurrentPoint = Vec2i(loc.x, loc.y);
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
		if ( (UITouchPhaseEnded == touch.phase) || ((UITouchPhaseCancelled == touch.phase)) )
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

@end
