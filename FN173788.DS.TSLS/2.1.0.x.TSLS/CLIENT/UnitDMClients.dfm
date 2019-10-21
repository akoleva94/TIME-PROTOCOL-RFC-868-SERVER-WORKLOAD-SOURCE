object dmClients: TdmClients
  OldCreateOrder = False
  Height = 115
  Width = 596
  object csOut: TClientSocket
    Active = False
    Address = '127.0.0.1'
    ClientType = ctNonBlocking
    Port = 37
    OnConnect = csOutConnect
    OnDisconnect = csOutDisconnect
    OnRead = csOutRead
    OnError = csOutError
    Left = 56
    Top = 40
  end
end
