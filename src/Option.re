let component = ReasonReact.statelessComponent("Option");

let make = _children => {
    ...component,
    render: (_self) => {
        <div className=".c-reason-select__option">
        </div>
    }
}