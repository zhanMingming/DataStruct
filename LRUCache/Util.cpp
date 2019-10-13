#include"Util.h"
#include<stdlib.h>
#include<sys/time.h>

namespace zhanmm {

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}



long timeInSeconds(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec;
    // return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);

}

} //namespace zhanmm