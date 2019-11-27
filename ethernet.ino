
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

  //Serial.begin(9600);

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

    resetRequestDelayCount();

    // DEBUG Serial.println(count_without_requests);
    // DEBUG count_without_requests=0;

    delay(1); // necessary for my system

    bfill = ether.tcpOffset();
    char *data = (char *) Ethernet::buffer + pos;

    // DEBUG Serial.println("REQUEST ARRIVED");

    if (strncmp("GET /", data, 5) != 0) {

      // Unsupported HTTP request
      // 304 or 501 response would be more appropriate
      bfill.emit_p(http_Unauthorized);

    } else {

      data += 5;

      String str_data = String(data);
      //Serial.println(str_data);

      if (data[0] == ' ') {

        // Return home page
        homePage();

      } else if (str_data.indexOf("d=") >= 0) {

        // direction

        int mov_direction_pos = str_data.indexOf("d=");
        char mov_direction = str_data[mov_direction_pos + 2];

        // sides

        int side = 0;

        if (str_data.indexOf("s=") >= 0) {
          int mov_side_pos = str_data.indexOf("s=");
          char mov_side = str_data[mov_side_pos + 2];

          if (mov_side == 'b') {
            // both
            side = SIDE_BOTH;
          } else if (mov_side == 'l') {
            // left only
            side = SIDE_LEFT;
          } else if (mov_side == 'r') {
            // right only
            side = SIDE_RIGHT;
          }

        }

        if (mov_direction == 'u') {
          motor_up(side);
        } else if (mov_direction == 'd') {
          motor_down(side);
        }

        homePage();


      } else {

        // Page not found
        bfill.emit_p(http_Unauthorized);

      }
    }

    ether.httpServerReply(bfill.position()); // send http response
  }


}
