#ifndef SOCKET_H_
# define SOCKET_H_

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include "Winsock2.h"
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#include <functional>

#include "ISocket.hpp"
#include "NetManager.hpp"
#include <string>
#include <list>

/*!
 * \class UdpSocket
 * \brief Classe permettant l'utilisation d'un socket Udp BSD-Style de manière plateforme indépendante. Iplémente ISocket
 */

class UdpSocket : public ISocket
{
public:
  /*!
   * \brief Constructeur par défaut, exception safe sur Unix
   */
  UdpSocket() = delete;
  /*!
   * \brief Constructeur créant le socket, peut lancer des exceptions en cas d'erreur
   * \param port de destination des paquets
   */
  UdpSocket(int port);
  /*!
   * \brief Constructeur créant le socket, peut lancer des exceptions en cas d'erreur
   * \param port de destination des paquets
   * \param adresse de destination
   */
  UdpSocket(int port, std::string inetAddr);

  /*!
   * \brief Constructeur créant le socket, peut lancer des exceptions en cas d'erreur
   * \param port de destination des paquets
   * \param adresse de destination
   * \prama Pointeur sur un NetManager qui gèrera l'appel des fonctions asynchrones lors de la disponibilité des sockets
   */
  UdpSocket(int port, std::string inetAddr, NetManager*);

  /*!
   * \brief Destructeur. Ferme le socket et clean sous Windows
   */

  virtual ~UdpSocket();
  /*!
   * \brief change le NetManager qui gère les actions d'entrée / sortie du socket
   */
 void setManager(NetManager*);

  /*!
   * \brief Permet de modifier le port du socket et de l'initialiser
   * \param port à modifier
   */

  bool setPort(int port);

  /*!
   * \brief Permet de modifier l'adresse du socket et de l'initialiser
   * \param adresse à modifier
   */

  void setAddr(std::string netAddr);
  /*!
   * \brief permet le passage d'un socket en non bloquant
   */
  bool setNonBlocking();

  /*!
   * \brief envoie une chaine contenant des données à l'adresse donnée,
   * via le sendPort providé
   * \param data à envoyer
   * \return taille de la donnée écrite, ou -1 en cas d'erreur
   */
  size_t send(std::string const& data);

  /*!
   * \brief envoie des données contenues dans un buffer dès qu'il lui es possinble d'"écrire sur le réseau"
   * \param data à envoyer
   * \param callback pour gérer la réponse de l'envoi
   */

  void async_send(std::string const& data, sendHandler callback);
  /*!
   * \brief reçoit des données, et stocke les infos sur l'envoyeur dans _lastAddr
   * \param buffer pour stocker les données reçues
   */
  size_t receive(std::string& data);

  /*!
   * \brief fonction receive appleant le callback à la réception d'un packet
   * \param callback
   */
  void async_receive(std::string& buffer, receiveHandler callback);

  /*!
   * \brief renvoie l'adresse sous forme de chaine dottée de l'envoyeur du dernier paquet reçu
   */
  std::string getLastPackAddr() const;
  /*!
   * \brief renvoie le port via lequel est arrivé le dernier paquet reçu
   */
  int getLastPackPort() const;
  /*!
   * \brief change le port via lequel envoyer des données avec send
   */
  void setSendPort(int port);
  /*!
   * \brief boucle sur les I/O définis par les fonctions async
   */
  void loop();
private:

  /*!
   * \brief ferme le socket de manière plateforme indépendante
   */
  void closeSocket();
public:
  static constexpr unsigned int bufferSize = 512;

private:
  /*!
   * \brief port d'envoi des données
   */
  int _port;
  /*!
   * \brief socket descriptor sous_jacent pour interagir avec les appels systemes de réception
   */
  int _sd;
  /*!
   * \brief adresse servant à l'envoi des données via send
   */
  sockaddr_in _addr;
  /*!
   * \brief adresse stockant les informations sur l'envoyeur du dernier paquet
   */
  sockaddr_in _lastAddr;
  /*!
   * \brief pointeur sur le manager du socket
   */
  NetManager* _manager;
};

#endif /* !SOCKET_H_ */
