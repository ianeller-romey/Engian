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
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[RoomState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id])
)

CREATE TABLE [dbo].[ParagraphStates] (
	[Id] int PRIMARY KEY IDENTITY,
	[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id]),
	[State] int NOT NULL
)

CREATE TABLE [dbo].[Nouns] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id]),
	[ParagraphState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id])
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
	[MessageChoice] int FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id]),
	[Result] int NULL
)

CREATE TABLE [dbo].[Players] (
	[Email] varchar -- TODO: Break emails into fancy domain-specific table bullshit