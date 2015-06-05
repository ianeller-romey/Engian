USE [GinTub]

CREATE TABLE [dbo].[Areas] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[Locations] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[LocationFile] varchar(MAX) NOT NULL
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
	[State] int NOT NULL,
	[Time] datetime NULL,
	[Location] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Locations]([Id]),
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id])
)

CREATE TABLE [dbo].[Paragraphs] (
	[Id] int PRIMARY KEY IDENTITY,
	[Order] int NOT NULL,
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[RoomState] int NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id]),
	CONSTRAINT UQ__ParagraphsOrder UNIQUE NONCLUSTERED ([Order], [Room], [RoomState])
)

CREATE TABLE [dbo].[ParagraphStates] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[State] int NOT NULL,
	[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id])
	CONSTRAINT UQ__ParagraphStatesState UNIQUE NONCLUSTERED ([State], [Paragraph])
)

CREATE TABLE [dbo].[Nouns] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[ParagraphState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ParagraphStates]([Id])
)

CREATE TABLE [dbo].[VerbTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Move')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Take')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Use')

CREATE TABLE [dbo].[Verbs] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id])
)

CREATE TABLE [dbo].[ResultTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES ('Move')

INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES ('Item Acquisition')

INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES ('Event Acquisition')

INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES ('Character Acquisition')

INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES ('Paragraph State Change')

INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES ('Room State Change')

CREATE TABLE [dev].[ResultTypeJSONFields] (
	[Id] int PRIMARY KEY IDENTITY,
	[JSONField] varchar(MAX) NOT NULL,
	[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id])
)

CREATE TABLE [dbo].[Results] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[JSONData] varchar(MAX) NULL,
	[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id])
)

CREATE TABLE [dbo].[Actions] (
	[Id] int PRIMARY KEY IDENTITY,
	[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id]),
	[Noun] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Nouns]([Id])
)

CREATE TABLE [dbo].[ActionResults] (
	[Id] int PRIMARY KEY IDENTITY,
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id]),
	[Result] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id])
)

CREATE TABLE [dbo].[RequirementSourceTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

INSERT INTO [dbo].[RequirementSourceTypes] ([Name])
VALUES ('Item')

INSERT INTO [dbo].[RequirementSourceTypes] ([Name])
VALUES ('Event')

INSERT INTO [dbo].[RequirementSourceTypes] ([Name])
VALUES ('Character')

CREATE TABLE [dbo].[Requirements] (
	[Id] int PRIMARY KEY IDENTITY,
	[Requirement] int NOT NULL,
	[RequirementSourceType] int FOREIGN KEY REFERENCES [dbo].[RequirementSourceTypes]([Id]),
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
)

CREATE TABLE [dbo].[Messages] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[MessageChoices] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[Message] int FOREIGN KEY REFERENCES [dbo].[Messages]([Id])
)

CREATE TABLE [dbo].[MessageChoiceResults] (
	[Id] int PRIMARY KEY IDENTITY,
	[Result] int NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id]),
	[MessageChoice] int FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id])
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
	[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id]),
	[ParagraphStates] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ParagraphStates]([Id]),
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