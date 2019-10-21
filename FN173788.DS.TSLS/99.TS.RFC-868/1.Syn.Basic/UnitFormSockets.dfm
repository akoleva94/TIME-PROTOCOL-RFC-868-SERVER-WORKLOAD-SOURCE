object formSockets: TformSockets
  Left = 0
  Top = 0
  Caption = 'formSockets'
  ClientHeight = 110
  ClientWidth = 219
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 12
  object ssSocket: TServerSocket
    Active = False
    Port = 37
    ServerType = stNonBlocking
    OnClientConnect = ssSocketClientConnect
    OnClientDisconnect = ssSocketClientDisconnect
    OnClientError = ssSocketClientError
    Left = 40
    Top = 40
  end
  object csSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 37
    OnConnect = csSocketConnect
    OnDisconnect = csSocketDisconnect
    OnRead = csSocketRead
    OnError = csSocketError
    Left = 144
    Top = 40
  end
end
