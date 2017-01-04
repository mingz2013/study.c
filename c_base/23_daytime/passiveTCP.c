int passivesock(const char * service, const char * transport, int qlen);

int passiveTCP(const char * service){
	return passivesock(service, "TCP", qlen);
}