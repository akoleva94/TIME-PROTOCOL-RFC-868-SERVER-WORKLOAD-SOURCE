object formMain: TformMain
  Left = 0
  Top = 0
  Caption = 'Background Thread'
  ClientHeight = 132
  ClientWidth = 451
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object rgMode: TRadioGroup
    Left = 9
    Top = 12
    Width = 246
    Height = 78
    Caption = ' Mode '
    ItemIndex = 0
    Items.Strings = (
      'Single'
      'Background')
    TabOrder = 0
  end
  object buttonStart: TButton
    Left = 275
    Top = 17
    Width = 92
    Height = 31
    Caption = 'S T A R T'
    TabOrder = 1
    OnClick = buttonStartClick
  end
  object stbarClock: TStatusBar
    Left = 0
    Top = 113
    Width = 451
    Height = 19
    Panels = <
      item
        Width = 350
      end
      item
        Alignment = taCenter
        Width = 50
      end>
    SizeGrip = False
  end
  object timerClock: TTimer
    OnTimer = timerClockTimer
    Left = 273
    Top = 62
  end
end
