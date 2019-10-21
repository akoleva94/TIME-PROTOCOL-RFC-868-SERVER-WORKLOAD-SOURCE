object dmSockets: TdmSockets
  OldCreateOrder = False
  Height = 115
  Width = 596
  object csOut1: TClientSocket
    Active = False
    Address = '127.0.0.1'
    ClientType = ctNonBlocking
    Port = 37
    OnConnect = csOut1Connect
    OnDisconnect = csOut1Disconnect
    OnRead = csOut1Read
    OnError = csOut1Error
    Left = 56
    Top = 40
  end
  object csOut2: TClientSocket
    Active = False
    Address = '127.0.0.1'
    ClientType = ctNonBlocking
    Port = 37
    OnConnect = csOut1Connect
    OnDisconnect = csOut1Disconnect
    OnRead = csOut1Read
    OnError = csOut1Error
    Left = 141
    Top = 40
  end
  object csOut3: TClientSocket
    Active = False
    Address = '127.0.0.1'
    ClientType = ctNonBlocking
    Port = 37
    OnConnect = csOut1Connect
    OnDisconnect = csOut1Disconnect
    OnRead = csOut1Read
    OnError = csOut1Error
    Left = 226
    Top = 40
  end
  object csOut4: TClientSocket
    Active = False
    Address = '127.0.0.1'
    ClientType = ctNonBlocking
    Port = 37
    OnConnect = csOut1Connect
    OnDisconnect = csOut1Disconnect
    OnRead = csOut1Read
    OnError = csOut1Error
    Left = 312
    Top = 40
  end
end
