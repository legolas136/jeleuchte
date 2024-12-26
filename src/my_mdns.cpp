#include "my_mdns.h"
#include "definitions.h"

KnownVislinks vislink_data;

void setupMdns(const char *_hostname, const char *_instanceName)
{
    mdns_instance_name_set(_instanceName);
    if (!MDNS.begin(_hostname))
    {
        Serial.println("Error starting mDNS");
        return;
    }
    addMdnsService(1337, "vislink", "Linyo's Jeleuchte");
}

void discover_vislink_service()
{
    Serial.print("Scanning for Vislink stations: ");

    // int nrOfServices = MDNS.queryService(MY_MDNS_SERVICE_NAME, "tcp");
    int nrOfServices = MDNS.queryService("http", "tcp");
    if (nrOfServices == 0)
    {
        Serial.println("No services were found.");
    }
    // Serial.print("Number of services found: ");
    // Serial.println(nrOfServices);

    uint8_t nr_of_found_vislinks = 0;

    for (int i = 0; i < nrOfServices; i = i + 1)
    {
        // Serial.println("---------------");

        // Serial.print("Hostname: ");
        // Serial.println(MDNS.hostname(i));

        // Serial.print("IP address: ");
        // Serial.println(MDNS.IP(i));

        // Serial.print("Port: ");
        // Serial.println(MDNS.port(i));

        // Serial.print("Service Name: ");
        // Serial.println(MDNS.txt(i, "type"));

        // Serial.println("---------------");
        if (MDNS.txt(i, "type") == "vislink")
        {
            vislink_data.ips[nr_of_found_vislinks] = MDNS.IP(i);
            vislink_data.ports[nr_of_found_vislinks] = MDNS.port(i);
            vislink_data.descriptions[nr_of_found_vislinks] = MDNS.txt(i, "description");
            nr_of_found_vislinks++;
        }
    }

    vislink_data.amount_of_vislinks_found = nr_of_found_vislinks;

    Serial.println("ready!");
    Serial.print("Found ");
    Serial.print(vislink_data.amount_of_vislinks_found);
    Serial.println(" stations:");

    for (int i = 0; i < vislink_data.amount_of_vislinks_found; i++)
    {
        Serial.print(i);
        Serial.print("   ");
        Serial.print(vislink_data.descriptions[i]);
        Serial.print("   ");
        Serial.print(vislink_data.ips[i]);
        Serial.print(" : ");
        Serial.println(vislink_data.ports[i]);
    }

    Serial.println();
}

void addMdnsService(uint16_t _servicePort, const char *_serviceType, const char *_serviceDescription)
{
    Serial.print("Added mDNS Service: ");
    Serial.print(_serviceType);
    Serial.print(" : ");
    Serial.print(_serviceDescription);
    Serial.print(" on port: ");
    Serial.println(_servicePort);

    MDNS.addService("http", "tcp", _servicePort);

    MDNS.addServiceTxt("http", "tcp", "type", _serviceType);
    MDNS.addServiceTxt("http", "tcp", "description", _serviceDescription);
}
