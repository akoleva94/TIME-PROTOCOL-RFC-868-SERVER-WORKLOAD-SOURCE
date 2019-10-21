object formMain: TformMain
  Left = 0
  Top = 0
  Caption = 'Day Time (RFC-867) Server - Indy Realization'
  ClientHeight = 273
  ClientWidth = 411
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object gbSync: TGroupBox
    Left = 0
    Top = 0
    Width = 411
    Height = 105
    Align = alTop
    TabOrder = 0
    ExplicitLeft = 120
    ExplicitTop = 104
    ExplicitWidth = 185
    object buttonSync: TButton
      Left = 2
      Top = 15
      Width = 407
      Height = 88
      Align = alClient
      Caption = 'S Y N C'
      TabOrder = 0
      OnClick = buttonSyncClick
      ExplicitLeft = 168
      ExplicitTop = 40
      ExplicitWidth = 75
      ExplicitHeight = 25
    end
  end
  object memoLog: TMemo
    Left = 0
    Top = 105
    Width = 411
    Height = 168
    Align = alClient
    TabOrder = 1
    ExplicitLeft = 120
    ExplicitTop = 112
    ExplicitWidth = 185
    ExplicitHeight = 89
  end
  object IdDayTimeServer: TIdDayTimeServer
    Active = True
    Bindings = <>
    TimeZone = 'EST'
    Left = 48
    Top = 200
  end
  object IdDayTime: TIdDayTime
    Host = '127.0.0.1'
    Left = 152
    Top = 199
  end
end
