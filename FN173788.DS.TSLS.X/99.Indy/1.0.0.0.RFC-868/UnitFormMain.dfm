object formMain: TformMain
  Left = 0
  Top = 0
  Caption = 'Time Protocol (RFC-868) Server Indy Realization'
  ClientHeight = 231
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object IdTimeServer: TIdTimeServer
    Active = True
    Bindings = <>
    ListenQueue = 100
    BaseDate = 2.000000000000000000
    Left = 112
    Top = 152
  end
end