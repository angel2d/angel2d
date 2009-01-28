rem VC8
del Build\VC8\Box2D.ncb
del /a:H Build\VC8\Box2D.suo
del /s Build\VC8\*.user
rmdir /s /q Build\VC8\Box2D
rmdir /s /q Build\VC8\TestBed
rmdir /s /q Build\VC8\glui
rmdir /s /q Build\VC8\freeglut
rmdir /s /q Build\VC8\HelloWorld

rem Code::Blocks
del Library\libEngine.a
del Build\CodeBlocks\*.depend
del Build\CodeBlocks\*.layout
rmdir /s /q Build\CodeBlocks\obj
rmdir /s /q Build\CodeBlocks\bin
