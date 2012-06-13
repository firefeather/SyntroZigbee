//
//  Copyright (c) 2012 Pansenti, LLC.
//	
//  This file is part of Syntro
//
//  Syntro is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Syntro is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Syntro.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef ZIGBEECLIENT_H
#define ZIGBEECLIENT_H

#include <qlist.h>
#include <qqueue.h>

#include "SyntroLib.h"
#include "ZigbeeDevice.h"
#include "ZigbeeCommon.h"
#include "ZigbeeStats.h"

class ZigbeeClient : public Endpoint
{
	Q_OBJECT

public:
	ZigbeeClient(QObject *parent, QSettings *settings);

public slots:
	void receiveData(quint64 address, QByteArray data);
	void localRadioAddress(quint64 address);	
	void nodeDiscoverResponse(QList<ZigbeeStats>);

signals:
	void sendData(quint64 address, QByteArray data);
	void requestNodeDiscover();

protected:
	void appClientInit();
	void appClientBackground();
	void appClientReceiveE2E(int servicePort, SYNTRO_EHEAD *header, int length);

private:
	void issuePollRequests();
	void sendReceivedData();
	QByteArray getRxData(quint64 *address);
	void executeLocalRadioCommand(quint8 *request, int length);

	int m_multicastPort;
	int m_e2ePort;
	bool m_promiscuousMode;
	quint64 m_localZigbeeAddress;

	QMap<quint64, ZigbeeDevice *> m_devices;
	QMutex m_rxMutex;
	QQueue<QByteArray> m_rxQ;
	QQueue<quint64> m_rxAddressQ;

	QMap<quint64, int> m_badRxDevices;
	QMap<quint64, int> m_badTxDevices;
};

#endif // ZIGBEECLIENT_H
