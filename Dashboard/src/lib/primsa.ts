import { PrismaClient, type Data } from '@prisma/client'

export const prisma = new PrismaClient();

export const fetchLatestReading = async (): Promise<Data> => {
    const [data] = await prisma.data.findMany({
        take: 1,
        orderBy: {
            createdAt: "desc",
        }
    })

    return data;
}
