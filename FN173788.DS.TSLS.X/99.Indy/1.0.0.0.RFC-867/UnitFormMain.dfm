object formMain: TformMain
  Left = 0
  Top = 0
  Caption = 'DayTime(RFC-867) Server - Indy Realization'
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
    ExplicitLeft = 16
    ExplicitTop = 16
    ExplicitWidth = 185
    object btnSync: TButton
      Left = 2
      Top = 15
      Width = 407
      Height = 88
      Align = alClient
      Caption = 'S Y N C'
      TabOrder = 0
      OnClick = btnSyncClick
      ExplicitLeft = 128
      ExplicitTop = 32
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
    ExplicitLeft = 2
    ExplicitTop = 97
  end
  object IdDayTimeServer: TIdDayTimeServer
    Active = True
    Bindings = <>
    TimeZone = 'EST'
    Left = 40
    Top = 216
  end
  object IdDayTime: TIdDayTime
    OnWorkEnd = IdDayTimeWorkEnd
    Host = '127.0.0.1'
    Left = 128
    Top = 216
  end
end