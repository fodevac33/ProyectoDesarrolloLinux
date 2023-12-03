-- CreateTable
CREATE TABLE "Data" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "ambientTemp" REAL NOT NULL,
    "motorTemp" REAL NOT NULL,
    "latitude" REAL NOT NULL,
    "longitude" REAL NOT NULL
);
