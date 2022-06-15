#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

///////////////////////////////////////////////////////////////////////////////////////////
//                    Toggles                                                            //
///////////////////////////////////////////////////////////////////////////////////////////

// some chalmers signals have red-pcb 1.44" displays from creatron
// others use the cheaper blue-pcb 1.44" displays from aliexpress
static int display_color = 1; //(blue_pcb = 1; red_pcb = 2)

// for debugging it's useful to turn off the chalmers signal's internet-y abilities. That way we can do things like make changes with it's interface without waiting for it to connect to the internet
static bool enable_internet = true;

// earlier versions of chalmers signals don't have their button attached to the ESP. It's useful to be able to quickly turn off all features of the chalmers signal that use this button.
static bool has_button = true;

//
// Sync timer delays
//

// pull_from_cloud timer
// how long to wait (after the last time the dial was turned)
int pull_wait = 70000; // 70 seconds
int push_wait = 3000;  // 3 seconds

// how many millis to wait until support message is sent
int support_call_wait = 6000; // must be equal to (support_call_wait_seconds + 1)
// how many seconds to wait until support message is sent
int support_call_wait_seconds = 5;

int button_clicked_wait = 5000;
int button_clicked_wait_seconds = 5;
int button_clicked_debounce = 50;

#endif