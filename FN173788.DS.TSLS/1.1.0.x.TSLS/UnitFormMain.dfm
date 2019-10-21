object formMain: TformMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = ' Time Server Load Simulator'
  ClientHeight = 407
  ClientWidth = 494
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object panelShowHideProtocol: TPanel
    Left = 0
    Top = 342
    Width = 494
    Height = 12
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alBottom
    TabOrder = 0
    object labelShowHideLog: TLabel
      Left = 10
      Top = -1
      Width = 11
      Height = 12
      Cursor = crSizeNS
      Hint = 'Show/Hide Log'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = '+ '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = labelShowHideLogClick
    end
    object bevelShowHideProtokol: TBevel
      Left = 22
      Top = 4
      Width = 464
      Height = 2
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alCustom
      Anchors = [akLeft, akRight]
      Shape = bsBottomLine
      Style = bsRaised
      ExplicitWidth = 490
    end
  end
  object gboxSync: TGroupBox
    Left = 0
    Top = 354
    Width = 494
    Height = 53
    Align = alBottom
    TabOrder = 1
    object buttonSync: TButton
      Left = 2
      Top = 15
      Width = 490
      Height = 36
      Align = alClient
      Caption = 'S Y N C'
      TabOrder = 0
      OnClick = buttonSyncClick
    end
  end
  object gboxLog: TGroupBox
    Left = 0
    Top = 0
    Width = 494
    Height = 342
    Align = alClient
    Caption = ' Log '
    TabOrder = 2
    object memoLog: TMemo
      Left = 2
      Top = 15
      Width = 490
      Height = 325
      Align = alClient
      PopupMenu = pupLog
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object pupLog: TPopupMenu
    Left = 24
    Top = 32
    object miClear: TMenuItem
      Caption = 'Clear'
      OnClick = miClearClick
    end
  end
end
