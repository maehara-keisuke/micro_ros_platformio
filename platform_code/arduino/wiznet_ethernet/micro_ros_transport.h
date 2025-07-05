#include <Ethernet.h>

struct micro_ros_agent_locator {
	IPAddress address;
	int port;
};

static inline void set_microros_wiznet_ethernet_transports(byte mac[], IPAddress client_ip, IPAddress agent_ip, uint16_t agent_port, uint8_t slave_select_pin, bool use_dhcp, IPAddress& client_dynamic_ip){

	static struct micro_ros_agent_locator locator;

	Ethernet.init(slave_select_pin);

	if (use_dhcp == true){
		Ethernet.begin(mac);
		client_dynamic_ip = Ethernet.localIP();
	} else {
		Ethernet.begin(mac, client_ip);
	}
	delay(1000);

	locator.address = agent_ip;
	locator.port = agent_port;

	rmw_uros_set_custom_transport(
		false,
		&locator,
		platformio_transport_open,
		platformio_transport_close,
		platformio_transport_write,
		platformio_transport_read
	);
}
