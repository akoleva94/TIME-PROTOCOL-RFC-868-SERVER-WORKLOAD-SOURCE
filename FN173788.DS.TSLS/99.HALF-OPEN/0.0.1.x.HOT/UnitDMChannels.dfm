object dmChannels: TdmChannels
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Height = 359
  Width = 555
  object csMasterToSlave1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = csMasterToSlave1Connect
    OnDisconnect = csMasterToSlave1Disconnect
    OnRead = csMasterToSlave1Read
    OnError = csMasterToSlave1Error
    Left = 72
    Top = 252
  end
  object csMasterToSlave2: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = csMasterToSlave1Connect
    OnDisconnect = csMasterToSlave1Disconnect
    OnRead = csMasterToSlave1Read
    OnError = csMasterToSlave1Error
    Left = 192
    Top = 252
  end
  object csMasterToSlave3: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = csMasterToSlave1Connect
    OnDisconnect = csMasterToSlave1Disconnect
    OnRead = csMasterToSlave1Read
    OnError = csMasterToSlave1Error
    Left = 312
    Top = 252
  end
  object csMasterToSlave4: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = csMasterToSlave1Connect
    OnDisconnect = csMasterToSlave1Disconnect
    OnRead = csMasterToSlave1Read
    OnError = csMasterToSlave1Error
    Left = 432
    Top = 252
  end
  object ssInTarget: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = ssInTargetClientConnect
    OnClientDisconnect = ssInTargetClientDisconnect
    OnClientRead = ssInTargetClientRead
    OnClientError = ssInTargetClientError
    Left = 258
    Top = 31
  end
  object ssInSlave: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = ssInSlaveClientConnect
    OnClientDisconnect = ssInSlaveClientDisconnect
    OnClientRead = ssInSlaveClientRead
    OnClientError = ssInSlaveClientError
    Left = 258
    Top = 196
  end
  object csClient: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = csClientConnect
    OnDisconnect = csClientDisconnect
    OnRead = csClientRead
    OnError = csClientError
    Left = 258
    Top = 117
  end
end
