#include <VirtualWire.h>

#define channel 1
#define channelAlias "C"

// pins definitions
#define receivePin 2 
 
// interval at which ping should be received (milliseconds)
const long interval = 1000;
// will store last time ping was received
unsigned long previousMillis = 0;


class Receiver
{
	public:

		const char* PSS_RX			= "rx";
		const char* PSS_RY			= "ry";
		const char* PSS_LX			= "lx";
		const char* PSS_LY			= "ly";

		const char* PSB_SELECT		= "se";
		const char* PSB_L3			= "l3";
		const char* PSB_R3			= "r3";
		const char* PSB_START		= "st";
		const char* PSB_PAD_UP		= "up";
		const char* PSB_PAD_RIGHT	= "rt";
		const char* PSB_PAD_DOWN	= "dn";
		const char* PSB_PAD_LEFT	= "lt";
		const char* PSB_L2			= "l2";
		const char* PSB_R2			= "r2";
		const char* PSB_L1			= "l1";
		const char* PSB_R1			= "r1";
		const char* PSB_TRIANGLE	= "tr";
		const char* PSB_CIRCLE		= "ci";
		const char* PSB_CROSS		= "cr";
		const char* PSB_SQUARE		= "sq";
};

Receiver receiver;

void setup()
{
	Serial.begin(9600);

  
	// set data for VirtualWire library
    vw_set_rx_pin(receivePin);
    vw_setup(2000);   
	// start receiving data
	vw_rx_start();			
}
 
void loop()
{
	// check if got message
	checkMessage();

	if (millis() - previousMillis >= interval)
	{
		Serial.println("Signal lost!");
	}
}

void checkMessage()
{
	// get message from radio (add 1 for final 0)
	uint8_t buf[VW_MAX_MESSAGE_LEN + 1];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	buf[0] = '\0';

// C:1|P1:100|P2:1023

	if (vw_get_message(buf, &buflen))
	{
		// save last send time for ping timer
		previousMillis = millis();

		// Add the final 0 to end the C string
		buf[VW_MAX_MESSAGE_LEN] = 0;

		// Read each command pair
		char* command = strtok((char *)buf, "|");
		while (command != 0)
		{
			// Split the command in two values
			char* separator = strchr(command, ':');
			if (separator != 0)
			{
				// Actually split the string in 2: replace ':' with 0
				*separator = 0;
				char* element = command;
				++separator;
				int value = atoi(separator);

				// assuming that channel is placed at the begining of message
				if (strcmp(element, channelAlias) == 0)
				{
					// wrong channel, stop execution
					if (value != channel)
						return;
				}
				else if (strcmp(element, receiver.PSS_RX) == 0)
				{
					// debug
					int test_RX = value;
					Serial.println("PSS_RX: " + String(value));					
				}
				else if (strcmp(element, receiver.PSS_RY) == 0)
				{
					// debug
					int test_RY = value;
					Serial.println("PSS_RY: " + String(value));
				}
				else if (strcmp(element, receiver.PSS_LX) == 0)
				{
					// debug
					int test_LX = value;
					Serial.println("PSS_LX: " + String(value));
				}
				else if (strcmp(element, receiver.PSS_LY) == 0)
				{
					// debug
					int test_LY = value;
					Serial.println("PSS_LY: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_SELECT) == 0)
				{
					// debug
					Serial.println("PSB_SELECT: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_L3) == 0)
				{
					// debug
					Serial.println("PSB_L3: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_R3) == 0)
				{
					// debug
					Serial.println("PSB_R3: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_START) == 0)
				{
					// debug
					Serial.println("PSB_START: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_PAD_UP) == 0)
				{
					// debug
					Serial.println("PSB_PAD_UP: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_PAD_RIGHT) == 0)
				{
					// debug
					Serial.println("PSB_PAD_RIGHT: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_PAD_DOWN) == 0)
				{
					// debug
					Serial.println("PSB_PAD_DOWN: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_PAD_LEFT) == 0)
				{
					// debug
					Serial.println("PSB_PAD_LEFT: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_L2) == 0)
				{
					// debug
					Serial.println("PSB_L2: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_R2) == 0)
				{
					// debug
					Serial.println("PSB_R2: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_L1) == 0)
				{
					// debug
					Serial.println("PSB_L1: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_R1) == 0)
				{
					// debug
					Serial.println("PSB_R1: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_TRIANGLE) == 0)
				{
					// debug
					Serial.println("PSB_TRIANGLE: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_CIRCLE) == 0)
				{
					// debug
					Serial.println("PSB_CIRCLE: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_CROSS) == 0)
				{
					// debug
					Serial.println("PSB_CROSS: " + String(value));
				}
				else if (strcmp(element, receiver.PSB_SQUARE) == 0)
				{
					// debug
					Serial.println("PSB_SQUARE: " + String(value));
				}
			}
			// Find the next command in input string
			command = strtok(0, "|");
		}
	}
}