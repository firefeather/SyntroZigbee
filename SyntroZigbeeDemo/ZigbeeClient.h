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

#include "SyntroLib.h"
#include "ZigbeeCommon.h"
#include "ZigbeeStats.h"


class ZigbeeClient : public Endpoint
{
	Q_OBJECT

public:
	ZigbeeClient(QObject *parent, QSettings *settings);

	bool sendData(quint64 address, QByteArray data);

signals:
	void receiveData(quint64 address, QByteArray data);
	void receiveRadioList(QList<ZigbeeStats>);

protected:
	void appClientInit();
	void appClientReceiveMulticast(int servicePort, SYNTRO_EHEAD *multicast, int len);

private:
	void processRadioList(QByteArray data);

	int m_receivePort;
	int m_controlPort;
};

#endif // ZIGBEECLIENT_H
