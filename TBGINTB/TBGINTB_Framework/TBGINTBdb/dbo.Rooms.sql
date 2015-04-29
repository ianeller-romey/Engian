CREATE TABLE [dbo].[Rooms]
(
	[Id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [Name] VARCHAR(100) NOT NULL, 
    [X] INT NOT NULL,
    [Y] INT NOT NULL,
	[Z] INT NOT NULL,
    [Text] VARCHAR(MAX) NOT NULL
)

GO

CREATE INDEX [IX_Rooms_X] ON [dbo].[Rooms] ([X])

GO

CREATE INDEX [IX_Rooms_Y] ON [dbo].[Rooms] ([Y])
