#ifndef _GNU_TIME_H_
#define _GNU_TIME_H_

#ifndef _WINSOCK_H
struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

#endif /* _WINSOCK_H */

#endif /* _GNU_TIME_H_ */
