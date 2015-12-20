#ifndef ISOCKET_H_
# define ISOCKET_H_

#include <string>
#include <functional>

#ifdef _WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

/*!
 * \class ISocket
 * \brief Interface permettant d'interagir avec n'imprte quel type de socket
 */

class ISocket
{
public:
  enum returnCode {
    Timeout = 0,
    Fail,
    Incomplete,
    UndefFD,
    Sucess,
  };
  typedef std::function<void(ISocket::returnCode, ssize_t)> sendHandler;
  typedef std::function<void(ISocket::returnCode, ssize_t, std::string, int)> receiveHandler;
  virtual ~ISocket() {};
  virtual bool setPort(int port) = 0;
  virtual void setAddr(std::string addr) = 0;
  virtual void async_send(std::string const& data, sendHandler callback, std::string addr, int port) = 0;
  virtual ssize_t send(std::string const& data) = 0;
  virtual void async_receive(std::string& buffer, receiveHandler callback) = 0;
  virtual ssize_t receive(std::string& data) = 0;
  virtual bool setNonBlocking() = 0;
  virtual void setSendPort(int port) = 0;
  virtual std::string getLastPackAddr() const = 0;
  virtual int getLastPackPort() const = 0;
};

#endif /* !ISOCKET_H_ */
