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

#import "AngelAppDelegate.h"

#import "AngelViewController.h"


// how many samples per second we'll take from the accelerometer per second
#define ANGEL_ACCEL_UPDATE_FREQ 20.0f

// This is how many samples will get averaged to send as a single number to
//  the Angel runtime. A larger buffer means more lag, but smoother motion. 
#define ANGEL_ACCEL_BUFFER_SIZE 10

bool __angelAccelBufferInitted = false;
Vector3 __angelAccelBuffer[ANGEL_ACCEL_BUFFER_SIZE];


@implementation AngelAppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;

- (void)dealloc
{
	[_window release];
	[_viewController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	UIAccelerometer* accelerometer = [UIAccelerometer sharedAccelerometer];
	[accelerometer setDelegate:self];
	[accelerometer setUpdateInterval: 1.0f / ANGEL_ACCEL_UPDATE_FREQ];
	
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
	    self.viewController = [[[AngelViewController alloc] initWithNibName:@"AngelViewController_iPhone" bundle:nil] autorelease];
	} else {
	    self.viewController = [[[AngelViewController alloc] initWithNibName:@"AngelViewController_iPad" bundle:nil] autorelease];
	}
	self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
	// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
	
	Vector3 averagedAccel;
	
	if (!__angelAccelBufferInitted)
	{
		for (int i=0; i < ANGEL_ACCEL_BUFFER_SIZE; i++)
		{
			__angelAccelBuffer[i].X = acceleration.x;
			__angelAccelBuffer[i].Y = acceleration.y;
			__angelAccelBuffer[i].Z = acceleration.z;
		}
		averagedAccel = __angelAccelBuffer[0];
		__angelAccelBufferInitted = true;
	}
	else 
	{
		// rotate out
		for (int i=ANGEL_ACCEL_BUFFER_SIZE - 1; i > 0; i--)
		{
			__angelAccelBuffer[i] = __angelAccelBuffer[i-1];
			averagedAccel += __angelAccelBuffer[i];
		}
		__angelAccelBuffer[0].X = acceleration.x;
		__angelAccelBuffer[0].Y = acceleration.y;
		__angelAccelBuffer[0].Z = acceleration.z;
		averagedAccel += __angelAccelBuffer[0];
		averagedAccel /= ANGEL_ACCEL_BUFFER_SIZE;
	}
	
	float savedX = averagedAccel.X;
	averagedAccel.X = -averagedAccel.Y;
	averagedAccel.Y = savedX;
	
	Accelerometer::GetInstance().NewAcceleration(averagedAccel);
}

@end
