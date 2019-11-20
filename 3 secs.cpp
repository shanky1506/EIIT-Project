switch (state)
    {
    case 1: /* IDLE State with tap Closed */

          tapClose(servo1);
          if(cm1<margin1 && cm1 != 0) //An object is present
          {
             a++;
          }
          if(a == 3)
          {
            state = 2 ;
          }

          break;
    case 2: /* Tap opening */

          tapOpen(servo1);
          a = 0;
          state = 3;
          s2i = cm2; // Taking the initial reading
          break;
    case 3: /* IDLE Tap open  */

          if(cm1 > margin1 || cm1 == 0)  // No Object is Placed at the Station
          {
            state = 4;
          }
//          if(cm2 < dbtwsens) // Extra 5 is for lag
//          {
//            state = 4;
//          }
//          // if(time > long_time)
          // {
          //   state =4;
          // }
          break;
    case 4: /* Tap Closing */

          s2f = cm2 ;
          tapClose(servo1);
          state =1;
          break;
    }