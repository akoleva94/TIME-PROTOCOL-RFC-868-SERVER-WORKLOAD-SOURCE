object formMain: TformMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'TimeProtocol [RFC868] - TThread Extended Release X'
  ClientHeight = 348
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
    Height = 213
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alClient
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
    ExplicitHeight = 211
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
      Left = 225
      Top = 14
      Width = 264
      Height = 91
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alClient
      Caption = ' Synchronize '
      TabOrder = 0
      object labelIPAddress: TLabel
        Left = 15
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
        Left = 14
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
        Left = 157
        Top = 32
        Width = 98
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
      Width = 223
      Height = 91
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alLeft
      Caption = ' UTC '
      TabOrder = 1
      object leditUTC: TLabeledEdit
        Left = 11
        Top = 33
        Width = 197
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
        Left = 11
        Top = 59
        Width = 63
        Height = 16
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Caption = 'Set Time'
        TabOrder = 1
      end
      object cbUTC: TCheckBox
        Left = 120
        Top = 59
        Width = 39
        Height = 17
        Caption = 'UTC'
        TabOrder = 2
        OnClick = cbUTCClick
      end
      object cbLog: TCheckBox
        Left = 169
        Top = 59
        Width = 39
        Height = 17
        Caption = 'Log'
        TabOrder = 3
        OnClick = cbLogClick
      end
    end
  end
  object stbarThreads: TStatusBar
    Left = 0
    Top = 320
    Width = 491
    Height = 28
    Panels = <
      item
        Alignment = taRightJustify
        Text = 'Max Number of Threads'
        Width = 200
      end
      item
        Text = '0'
        Width = 50
      end>
    SimpleText = 'MaxNumberOfThreads'
    OnDblClick = stbarThreadsDblClick
    ExplicitTop = 352
  end
end
