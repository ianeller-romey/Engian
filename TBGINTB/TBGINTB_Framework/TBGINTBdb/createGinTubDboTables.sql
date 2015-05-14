USE [GinTub]

CREATE TABLE [dbo].[Areas] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[Locations] (
	[Id] int PRIMARY KEY IDENTITY,
	[Location] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[Rooms] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[X] int NOT NULL,
	[Y] int NOT NULL,
	[Z] int NOT NULL,
	[Area] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Areas]([Id])
)

CREATE TABLE [dbo].[RoomStates] (
	[Id] int PRIMARY KEY IDENTITY,
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[State] int NOT NULL,
	[Location] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Locations]([Id]),
	[Time] datetime NULL
)

CREATE TABLE [dbo].[Paragraphs] (
	[Id] int IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[RoomState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id]),
	[State] int NOT NULL,
	CONSTRAINT PK__ParagraphsID__COMPOSITE PRIMARY KEY ([Id],[State])
)

CREATE TABLE [dbo].[Nouns] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[Paragraph] int NOT NULL,
	[ParagraphState] int NOT NULL,
	FOREIGN KEY ([Paragraph], [ParagraphState]) REFERENCES [dbo].[Paragraphs]([Id], [State])
)

CREATE TABLE [dbo].[VerbTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[Verbs] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id])
)

CREATE TABLE [dbo].[Actions] (
	[Id] int PRIMARY KEY IDENTITY,
	[Noun] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Nouns]([Id]),
	[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id])
)

CREATE TABLE [dbo].[ResultTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[ResultSourceTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[Results] (
	[Id] int PRIMARY KEY IDENTITY,
	[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id]),
	[ResultSourceType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultSourceTypes]([Id]),
	[Source] int NOT NULL,
	[JSONData] varchar(MAX) NULL
)

CREATE TABLE [dbo].[RequirementSourceTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[Requirements] (
	[Id] int PRIMARY KEY IDENTITY,
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id]),
	[RequirementSourceType] int FOREIGN KEY REFERENCES [dbo].[RequirementSourceTypes]([Id]),
	[Requirement] int NOT NULL
)

CREATE TABLE [dbo].[Messages] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[MessageChoices] (
	[Id] int PRIMARY KEY IDENTITY,
	[Message] int FOREIGN KEY REFERENCES [dbo].[Messages]([Id]),
	[Text] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[MessageChoiceOutcomes] (
	[Id] int PRIMARY KEY IDENTITY,
	[MessageChoice] int FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id]),
	[Result] int NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id])
)

CREATE TABLE [dbo].[EmailUserNames] (
	[Id] int PRIMARY KEY IDENTITY,
	[UserName] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[EmailDomainNames] (
	[Id] int PRIMARY KEY IDENTITY,
	[DomainName] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[EmailDomains] (
	[Id] int PRIMARY KEY IDENTITY,
	[Domain] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[Players] (
	[EmailUserName] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailUserNames]([Id]),
	[EmailDomainName] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailDomainNames]([Id]),
	[EmailDomain] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailDomains]([Id]),
	[Password] varchar(MAX) NOT NULL,
	[Id] uniqueidentifier NOT NULL PRIMARY KEY,
	[LastCheckpoint] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerRoomStates] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[RoomState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id]),
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerParagraphStates] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Paragraph] int NOT NULL,
	[ParagraphState] int NOT NULL,
	FOREIGN KEY ([Paragraph], [ParagraphState]) REFERENCES [dbo].[Paragraphs]([Id], [State]),
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[Items] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[Description] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[PlayerInventory] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Item] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Items]([Id]),
	[Active] bit NOT NULL,
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[Events] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[Description] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[PlayerHistory] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Event] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Events]([Id]),
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[Characters] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[Description] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[PlayerParty] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Character] int NOT NULL FOREIGN KEY REFERENCES [dbo].[characters]([Id]),
	[Active] bit NOT NULL,
	[CheckpointDate] datetime NOT NULL
)