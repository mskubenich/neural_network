object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 600
  ClientWidth = 1084
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    1084
    600)
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 8
    Top = 368
    Width = 1068
    Height = 224
    Hint = 'mm'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsItalic]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Learn: TButton
    Left = 8
    Top = 207
    Width = 238
    Height = 66
    Caption = 'Learn'
    TabOrder = 1
    OnClick = LearnClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 241
    Height = 201
    Caption = #1055#1088#1086#1077#1082#1090#1091#1074#1072#1085#1085#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label1: TLabel
      Left = 11
      Top = 16
      Width = 95
      Height = 16
      Caption = #1050#1110#1083#1100#1082#1110#1089#1090#1100' '#1096#1072#1088#1110#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 11
      Top = 38
      Width = 62
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = Edit1Change
      OnKeyPress = Edit1KeyPress
    end
    object ScrollBox1: TScrollBox
      Left = 3
      Top = 65
      Width = 235
      Height = 133
      VertScrollBar.Smooth = True
      VertScrollBar.Tracking = True
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object Edit2: TEdit
        Left = 85
        Top = 40
        Width = 121
        Height = 21
        TabOrder = 0
        Text = 'Edit2'
        Visible = False
      end
    end
    object Button2: TButton
      Left = 112
      Top = 34
      Width = 115
      Height = 25
      Caption = #1057#1090#1074#1086#1088#1080#1090#1080' '#1084#1077#1088#1077#1078#1091
      TabOrder = 2
      OnClick = Button2Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 252
    Top = 0
    Width = 824
    Height = 362
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = #1043#1088#1072#1092#1110#1095#1085#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1085#1103
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentColor = False
    ParentFont = False
    TabOrder = 3
    object ScrollBox2: TScrollBox
      Left = 2
      Top = 15
      Width = 820
      Height = 345
      HorzScrollBar.Tracking = True
      VertScrollBar.Tracking = True
      Align = alClient
      BorderStyle = bsNone
      Color = clBtnHighlight
      ParentColor = False
      TabOrder = 0
      ExplicitWidth = 728
      ExplicitHeight = 479
      object Image1: TImage
        Left = 3
        Top = 0
        Width = 483
        Height = 377
      end
    end
  end
end
