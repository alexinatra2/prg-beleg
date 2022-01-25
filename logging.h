#ifndef __LOG
#define __LOG

#define LOGGING 0
#define VERBOSE_LOGGING 0

#define LOG(x) printf("%s", x)
#define LOG_YELLOW(x) printf("\033[0;33m%s\033[0m", x)
#define LOG_RED(x) printf("\033[0;31m%s\033[0m", x)

#endif // !LOG