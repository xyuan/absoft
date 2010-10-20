#include <windows.h>
#include "unistd.h"

long ProcSpeedRead()
{
  char Buffer[_MAX_PATH];
  DWORD BufSize = _MAX_PATH;
  DWORD dwMHz = _MAX_PATH;
  HKEY hKey;
  long lError;

  // open the key where the proc speed is hidden:
  lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                        0,
                        KEY_READ,
                        &hKey);
    
  if(lError != ERROR_SUCCESS){
           return 0;
  }

  // query the key:
  RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE) &dwMHz, &BufSize);

  // convert the DWORD to a CString:
  dwMHz = dwMHz * 1000000;

  return (long) dwMHz;
}

long sysconf(int name)
{
   SYSTEM_INFO system_info;
   LARGE_INTEGER nFrequence;
   
   if( name == _SC_CLK_TCK ){
   	/* get cycle ticks per second */
   	QueryPerformanceCounter( &nFrequence );
	if( nFrequence.QuadPart != 0 ){
		return (long) nFrequence.QuadPart;
	}else{
		return ProcSpeedRead();
	}
   }else if( name == _SC_NPROCESSORS_ONLN ){
   	/* get the number of logical processors */
   	GetSystemInfo( &system_info );
   	return system_info.dwNumberOfProcessors;
   }
   
   return -1;
}
