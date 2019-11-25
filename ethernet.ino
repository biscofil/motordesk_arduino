
#include <EtherCard.h>


// ethernet interface ip address
static byte myip[] = { 192, 168, 1, 204 };
// gateway ip address
static byte gwip[] = { 192, 168, 1, 1 };

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer
BufferFiller bfill;


const char http_OK[] PROGMEM =
  "HTTP/1.0 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Pragma: no-cache\r\n\r\n";

const char http_Found[] PROGMEM =
  "HTTP/1.0 302 Found\r\n"
  "Location: /\r\n\r\n";

const char http_Unauthorized[] PROGMEM =
  "HTTP/1.0 401 Unauthorized\r\n"
  "Content-Type: text/html\r\n\r\n"
  "<h1>401 Unauthorized</h1>";

void homePage()
{
  bfill.emit_p(PSTR("$F"
                    //"<meta http-equiv='refresh' content='5'/>"
                    "<title>Motor Desk</title>"
                    "OK"),
               http_OK
              );


}



void ethernet_setup() {

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {

    //Serial.println( "Failed to access Ethernet controller");

  } else {

    ether.staticSetup(myip, gwip);

    setAsReady();

  }


}

void ethernet_loop() {
  
  // wait for an incoming TCP packet, but ignore its contents
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if (pos) {
   
    delay(1); // necessary for my system
    bfill = ether.tcpOffset();
    char *data = (char *) Ethernet::buffer + pos;
    
    if (strncmp("GET /", data, 5) != 0) {
      
      // Unsupported HTTP request
      // 304 or 501 response would be more appropriate
      bfill.emit_p(http_Unauthorized);
      
    }else {
      
      data += 5;
      
      /*Serial.println("INIZIO DATA");
         Serial.println(data);
         Serial.println("FINE DATA");*/
         
      if (data[0] == ' ') {
        
        // Return home page
        homePage();
        
      } else if (strncmp("?up=", data, 4) == 0) {

        motor_up();

        /*String str_data = String(data);
          int pos = str_data.indexOf("?hex=");
          String hex = str_data.substring(pos + 5, pos + 11);

          Serial.println(hex);

          long number = (long) strtol( &hex[0], NULL, 16);

          col_x[0] = number >> 16;
          col_x[1] = number >> 8 & 0xFF;
          col_x[2] = number & 0xFF;*/

        homePage();
        
      } else if (strncmp("?down=", data, 6) == 0) {
        
        motor_down();

      } else {
        
        // Page not found
        bfill.emit_p(http_Unauthorized);
        
      }
    }

    ether.httpServerReply(bfill.position()); // send http response
  }


}
