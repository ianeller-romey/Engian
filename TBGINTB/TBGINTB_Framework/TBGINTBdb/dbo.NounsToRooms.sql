CREATE TABLE [dbo].[NounsToRooms]
(
	[Noun] INT NOT NULL, 
    [Room] INT NOT NULL, 
    CONSTRAINT [FK_NounsToRooms_Nouns] FOREIGN KEY ([Noun]) REFERENCES [Nouns]([Id]), 
    CONSTRAINT [FK_NounsToRooms_Rooms] FOREIGN KEY ([Room]) REFERENCES [Rooms]([Id]) 
)

GO

CREATE INDEX [IX_NounsToRooms_Noun] ON [dbo].[NounsToRooms] ([Noun])

GO


CREATE INDEX [IX_NounsToRooms_Room] ON [dbo].[NounsToRooms] ([Room])
