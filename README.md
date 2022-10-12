# myspdlog
Wrapped DLL base on spdlog-1.10.0

* C style format syntax.
* `C 风格的格式化语法`
* Sync/Async logger with rotate file sink.
* `同步/异步模式，滚动日志`
* spdlog source code updated: rotate file mode supprting - asc|desc 
* `spdlog 源码更改：滚动日志文件支持设置按升序或降序生成`
* spdlog header files are not needed in your project.
* `已封装, 你的项目不用再包含 spdlog 头文件`
* VS2019 

# Example


```cpp
// main.cpp

#include "log_spd.h"

int main(int argc, char  *argv[])
{
	Logger logger, logger2;
	// Logger logger = Logger::createLogger("mylog.log", lv::trace, 100, 5);
	logger.setAsyncMode(false); 
	logger.init();
	logger.trace("Hello %s, you are the %dth visitor.", "Tony", 1);
	logger.flush();
	
	logger2 = logger;
	logger2.setAsyncMode(true);
	logger2.setFormat("%+");
	logger2.init("mylog.log");
	logger2.info("blasa bad w");
	logger2.flush();
	
	Logger::shutdown();
	return 0;
}
```
### log.log
>[2022-09-30 14:32:25.065][9532][trace] Hello Tony, you are the 1th visitor.
### mylog.log
>[2022-09-30 14:32:25.069] [__log__1] [info] [log_wrapper.cpp:75] blasa bad woa
