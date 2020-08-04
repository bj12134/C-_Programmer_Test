#include "Cloud_Client.hpp.hpp"
#define STORE_FILE "./list.backup"
#define LISTEN_FILE "./backup/"
#define SRV_IP "192.168.174.132"
#define SRV_PORT 9000

int main() {
	CloudClient client(STORE_FILE, LISTEN_FILE, SRV_IP, SRV_PORT);
	client.Start();
	return 0;
}