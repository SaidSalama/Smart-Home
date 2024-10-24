

void pin_direction(char DDrX, char pin, char state);
void pin_set(char pinX,char pin);
void pin_reset(char pinX,char pin);
void port_direction( char DDrX, char state);
char port_read(char pinX);
void port_write( char base,char value);
char pin_read(char pinX,char pin);
void pin_write(char base,char pin,char value);
void Delay_half_sec();