#include "multicast.h"
#include "log.h"

#include <QObject>
#include <QThread>
#include <QTimer>
#include <iostream>


Multicast::Multicast(QString id, const QHostAddress& address, uint16_t port)
    : m_id(id),
      m_hostAddress(address),
      m_port(port)
{
    m_multicastSocket = new QUdpSocket(this);
    bool success = m_multicastSocket->bind(QHostAddress::AnyIPv4, m_port, QUdpSocket::ShareAddress);
    if (!success)
    {
        trace->critical("multicast bind failed");
    }
    success = m_multicastSocket->joinMulticastGroup(m_hostAddress);
    if (!success)
    {
        trace->critical("multicast join failed");
    }

    connect(m_multicastSocket, &QUdpSocket::readyRead, this, &Multicast::slotMulticastRx);
}


void Multicast::tx(MulticastTxPacket &tx)
{
    QByteArray data = tx.getData(false);
    m_multicastSocket->writeDatagram(data.data(), data.size(), m_hostAddress, m_port);
}


void Multicast::slotMulticastRx()
{
    while (m_multicastSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_multicastSocket->pendingDatagramSize());
        m_multicastSocket->readDatagram(datagram.data(), datagram.size());
        MulticastRxPacketPtr received = MulticastRxPacketPtr(new MulticastRxPacket(datagram));
        emit rx(received);
    }
}
