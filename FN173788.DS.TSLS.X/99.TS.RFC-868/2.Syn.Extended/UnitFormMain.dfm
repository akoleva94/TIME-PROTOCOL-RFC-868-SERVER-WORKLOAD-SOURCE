object formMain: TformMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'TimeProtocol [RFC868] - Extended Release'
  ClientHeight = 320
  ClientWidth = 491
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 12
  object memoLogs: TMemo
    Left = 0
    Top = 107
    Width = 491
    Height = 211
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alTop
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object gbControl: TGroupBox
    Left = 0
    Top = 0
    Width = 491
    Height = 107
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alTop
    TabOrder = 1
    object gbSync: TGroupBox
      Left = 229
      Top = 14
      Width = 260
      Height = 91
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alRight
      Caption = ' Synchronize '
      TabOrder = 0
      object labelIPAddress: TLabel
        Left = 23
        Top = 19
        Width = 97
        Height = 12
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Caption = 'Server by IP Address'
      end
      object cboxIPAddress: TComboBox
        Left = 23
        Top = 33
        Width = 133
        Height = 20
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        ItemIndex = 0
        TabOrder = 0
        Text = '127.0.0.1'
        Items.Strings = (
          '127.0.0.1'
          '128.138.140.44')
      end
      object buttonSync: TButton
        Left = 176
        Top = 32
        Width = 69
        Height = 23
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Caption = 'SYNC'
        TabOrder = 1
        OnClick = buttonSyncClick
      end
    end
    object gbUTC: TGroupBox
      Left = 2
      Top = 14
      Width = 227
      Height = 91
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alLeft
      Caption = ' UTC '
      TabOrder = 1
      object leditUTC: TLabeledEdit
        Left = 38
        Top = 33
        Width = 174
        Height = 20
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        EditLabel.Width = 61
        EditLabel.Height = 12
        EditLabel.Margins.Left = 2
        EditLabel.Margins.Top = 2
        EditLabel.Margins.Right = 2
        EditLabel.Margins.Bottom = 2
        EditLabel.Caption = 'UTC received'
        TabOrder = 0
      end
      object cbSetTime: TCheckBox
        Left = 37
        Top = 59
        Width = 90
        Height = 16
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Caption = 'Set Time'
        TabOrder = 1
      end
    end
  end
end
