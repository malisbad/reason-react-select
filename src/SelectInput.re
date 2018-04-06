let component = ReasonReact.statelessComponent("SelectInput");

let make = _children => {
    ...component,
    render: (_self) => {
        <div className=".c-reason-select__input">
        </div>
    }
}