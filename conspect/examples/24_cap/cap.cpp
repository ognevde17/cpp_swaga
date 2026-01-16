#include <sys/capability.h>

cap_t caps = cap_get_proc();    
cap_clear(caps);
cap_set_flag(caps, CAP_EFFECTIVE, 1, (cap_value_t[]){CAP_NET_BIND_SERVICE}, CAP_SET);
cap_set_proc(caps);        

cap_free(caps);