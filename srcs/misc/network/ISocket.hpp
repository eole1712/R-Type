#ifndef ISOCKET_H_
# define ISOCKET_H_

#include <string>
#include <functional>

/*!
 * \class ISocket
 * \brief Interface permettant d'interagir avec n'imprte quel type de socket
 */

class ISocket
{
public:
  enum returnCode {
    Timeout,
    Fail,
    Incomplete,
    UndefFD,
    Sucess,
  };
  typedef std::function<void(ISocket::returnCode, size_t)> sendHandler;
  typedef std::function<void(ISocket::returnCode, size_t, std::string, int)> receiveHandler;
  virtual bool setPort(int port) = 0;
  virtual void setAddr(std::string addr) = 0;
  virtual size_t send(std::string const& data) = 0;
  virtual size_t receive(std::string& data) = 0;
  virtual bool setNonBlocking() = 0;
  virtual void setSendPort(int port) = 0;
  virtual std::string getLastPackAddr() const = 0;
  virtual int getLastPackPort() const = 0;
};

#endif /* !ISOCKET_H_ */