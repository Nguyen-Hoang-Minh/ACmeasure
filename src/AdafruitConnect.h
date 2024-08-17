#include <AdafruitIO.h> // tiến hành thêm thư viện AdafruitIO.h vào

#define IO_USERNAME  "kienpham"
#define IO_KEY       "aio_wVFt21Z1F38DyjYbP3aawGppG5aM"

#define WIFI_SSID "ACLAB" // Tên wifi để ESP 32 kết nối vào và truy cập đến server.
#define WIFI_PASS "ACLAB2023"  // Pass wifi

#include <AdafruitIO_WiFi.h>  // Khai báo thư viện AdafruitIO_WiFi.h để kết nối đến server.
extern AdafruitIO_WiFi io;  // Gọi hàm kết nối đến server.

// set up the 'digital' feed 
extern AdafruitIO_Feed *digital; // khai báo con trỏ digital để chứ dữ liệu lấy từ feed của server.
void handleMessage(AdafruitIO_Data *data);
void setupMQTT1();

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.

