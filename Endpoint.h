#include <string>

class Endpoint {

	private:
		std::string host;
		int port;

	public:
		Endpoint();
		Endpoint(std::string&, int);
		std::string getHost();
		int getPort();
		void setHost(std::string&);
		void setPort(int);
};
