#!/bin/sh

xcodebuild -configuration Release -sdk iphoneos4.3 -alltargets clean
xcodebuild -configuration Release -sdk iphoneos4.3 -alltargets build
cp build/Release-iphoneos/libFTGLES.a ./libFTGLES-arm.a

xcodebuild -configuration Release -sdk iphonesimulator4.3 -alltargets clean
xcodebuild -configuration Release -sdk iphonesimulator4.3 -alltargets build
cp build/Release-iphonesimulator/libFTGLES.a ./libFTGLES-sim.a

lipo -output libFTGLES.a -create libFTGLES-arm.a -arch i386 libFTGLES-sim.a
