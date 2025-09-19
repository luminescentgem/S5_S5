import type DTO         from "./DTO.js"
import type Query       from "./Query.js"

export default interface Repository {
    insert(dto: DTO): Promise<string>
    update(dto: DTO): Promise<string>
    find(query: Query): Promise<DTO>
    findAll(query: Query): Promise<DTO[]>
    delete(query: Query): Promise<DTO[]>
}