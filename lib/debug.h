#ifdef DEBUG
# define DEBUG_PRINT(x) sendString(x)
#else
#define DEBUG_PRINT(x) do {} while (0) 
#endif

void sendString(char* donnee);

void sendString(uint8_t donnee);
