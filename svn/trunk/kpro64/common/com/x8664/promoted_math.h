#include "fpu_control.h"
static float promoted_expf(float in){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = expf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_logf( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = logf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_log10f( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = log10f( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_asinf( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = asinf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_acosf( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = acosf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_sinhf( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = sinhf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_coshf( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = coshf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static float promoted_tanhf( float in ){
      int old_x87_mask;
      int new_x87_mask;
      float out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = tanhf( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_exp(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = exp( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_log(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = log( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_log10(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = log10( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_asin(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = asin( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_acos(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = acos( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_sinh(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = sinh( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_cosh(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = cosh( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}

static double promoted_tanh(double in){
      int old_x87_mask;
      int new_x87_mask;
      double out;
      new_x87_mask = 0x37f; // extended precision
      _FPU_GETCW( old_x87_mask );
      _FPU_SETCW( new_x87_mask );
      out = tanh( in );
      _FPU_SETCW( old_x87_mask );
      return out;
}





