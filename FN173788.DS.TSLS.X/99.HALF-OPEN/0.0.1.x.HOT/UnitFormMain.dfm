object formMain: TformMain
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Half-Open TCP Connections Tester'
  ClientHeight = 253
  ClientWidth = 475
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gboxLog: TGroupBox
    Left = 0
    Top = 0
    Width = 475
    Height = 181
    Align = alClient
    Caption = ' Log '
    TabOrder = 0
    object memoLog: TMemo
      Left = 2
      Top = 15
      Width = 471
      Height = 164
      Align = alClient
      PopupMenu = pupLog
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object gboxSync: TGroupBox
    Left = 0
    Top = 181
    Width = 475
    Height = 72
    Align = alBottom
    TabOrder = 1
    object buttonSync: TButton
      Left = 2
      Top = 15
      Width = 471
      Height = 55
      Align = alClient
      Caption = 'S Y N C'
      TabOrder = 0
      OnClick = buttonSyncClick
    end
  end
  object pupLog: TPopupMenu
    Left = 32
    Top = 40
    object miSave: TMenuItem
      Caption = 'Save'
      OnClick = miSaveClick
    end
  end
end
