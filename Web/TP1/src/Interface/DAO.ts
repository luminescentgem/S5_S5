import type Query       from "@/Interface/Query.js"
import type Entity      from "@/Interface/Entity.js"
import type DTO         from "./DTO.js"


export default interface DAO {
    exists(query: Query): Promise<boolean>
    find(query: Query): Promise<Entity>
    findAll(query: Query): Promise<Entity[]>
    update(entity: DTO): Promise<string>
    delete(query: Query): Promise<Entity[]>
}